#include "projectAnalyzer.h"

using namespace ProjectParser;

std::stringstream ProjectAnalyzer::Analyze(std::string path)
{
	auto start = std::chrono::system_clock::now();

	//take hardware core count for parallel parsing.
	unsigned hardware_concurrency = std::thread::hardware_concurrency();
	std::unique_ptr<std::thread[]> threads(new std::thread[hardware_concurrency]);

	Statistic stat;
	StringMutexQueue queue;
	bool is_done_searching(false);

	//start threads for parse
	for (unsigned i = 0; i < hardware_concurrency; i++)
	{
		threads[i] = std::thread(ProjectAnalyzer::ParseThread, std::ref(stat), std::ref(queue), std::ref(is_done_searching));
	}

	Scaner::Scan(path, std::regex(R"(^.*[.](c|cpp|h|hpp)$)"),
			[&queue] (std::string path) { queue.Add(path); },
			[&is_done_searching] { is_done_searching = true; });

	//after scan help parse by main thread
	ProjectAnalyzer::ParseThread(stat, queue, is_done_searching);

	//wait untill each thread end parsing
	for (unsigned i = 0; i < hardware_concurrency; i++)
	{
		threads[i].join();
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;

	return FormOutput(stat, elapsed_seconds.count());
}

std::stringstream ProjectAnalyzer::FormOutput
		(const Statistic& stat, double time)
{
	std::stringstream stream;

	stream << "Blank: " << stat.blank_lines << std::endl;
	stream << "Comment: " << stat.comment_lines << std::endl;
	stream << "Code: " << stat.code_lines << std::endl;
	stream << "Total: " << stat.line_count << std::endl;
	stream << "Files: " << stat.processed_files << std::endl;
	stream << "Elapsed time: " << time << "s" << std::endl;

	return stream;
}

void ProjectAnalyzer::ParseThread(Statistic& stat,
	StringMutexQueue& queue,
	const bool& is_done_searching)
{
	std::string parse_path;

	while (!is_done_searching || !queue.IsEmpty())
	{
		parse_path = queue.Pop();
		if (!parse_path.empty())
		{
			Parser::Parse(parse_path, stat);
		}
	}
}

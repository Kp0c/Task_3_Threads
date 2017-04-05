#include "projectAnalyzer.h"

namespace project_analyzer
{

std::shared_ptr<std::stringstream> ProjectAnalyzer::Analyze(std::string path)
{
	//note the time
	auto start = std::chrono::system_clock::now();

	//take hardware core count for parallel parsing.
	unsigned hardware_concurrency = std::thread::hardware_concurrency();
	std::thread* threads = new std::thread[hardware_concurrency];

	//initializating
	auto stat = std::make_shared<parser::Statistic>();
	auto queue = std::make_shared<StringMutexQueue>();
	auto is_done_searching = std::make_shared<bool>(false);

	//start threads for parse
	for(unsigned i = 0; i < hardware_concurrency; i++)
	{
		threads[i] = std::thread(ProjectAnalyzer::ParseThread, stat, queue, is_done_searching);
	}

	//start thread for scan
	scaner::Scaner::Scan(path, std::regex(R"(^.*[.](c|cpp|h|hpp)$)"),
			[&queue] (std::string path) { queue->Add(path); },
			[&is_done_searching] { *is_done_searching = true; });

	//after scan help parse by main thread
	ProjectAnalyzer::ParseThread(stat, queue, is_done_searching);

	//wait untill each thread end parsing
	for(unsigned i = 0; i < hardware_concurrency; i++)
	{
		threads[i].join();
	}

	delete[] threads;

	//note the time
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;

	return FormOutput(stat, elapsed_seconds.count());
}

std::shared_ptr<std::stringstream> ProjectAnalyzer::FormOutput(std::shared_ptr<const parser::Statistic> stat, double time)
{
	std::shared_ptr<std::stringstream> stream(new std::stringstream());

	*stream << "Blank: " << stat->blank_lines << std::endl;
	*stream << "Comment: " << stat->comment_lines << std::endl;
	*stream << "Code: " << stat->code_lines << std::endl;
	*stream << "Total: " << stat->line_count << std::endl;
	*stream << "Files: " << stat->processed_files << std::endl;
	*stream << "Elapsed time: " << time << "s" << std::endl;

	return stream;
}

void ProjectAnalyzer::ParseThread(std::shared_ptr<parser::Statistic> stat, std::shared_ptr<StringMutexQueue> queue,
				 std::shared_ptr<const bool> is_done_searching)
{
	std::string parse_path;

	while(!*is_done_searching || !queue->IsEmpty())
	{
		parse_path = queue->Pop();
		if(!parse_path.empty())
		{
			parser::Parser::Parse(parse_path, stat);
		}
	}
}

}

#include <UECS/World.h>

using namespace Ubpa;
using namespace std;

World::World()
	: entityMngr { this }
{
}

void World::Update() {
	schedule.Clear();
	for (auto job : jobs)
		jobPool.Recycle(job);
	jobs.clear();
	jobGraph.clear();

	for (const auto& [id, lifecycle] : systemMngr.lifecycleMap)
		lifecycle.OnUpdate(schedule);
	auto graph = schedule.GenSysFuncGraph();

	unordered_map<SystemFunc*, JobHandle> table;

	for (const auto& [v, adjVs] : graph.GetAdjList()) {
		auto job = jobPool.Request(v->Name());
		jobs.push_back(job);
		entityMngr.GenJob(job, v);
		table.emplace(v, jobGraph.composed_of(*job));
	}

	for (const auto& [v, adjVs] : graph.GetAdjList()) {
		auto vJob = table[v];
		for (auto adjV : adjVs)
			vJob.precede(table[adjV]);
	}

	executor.run(jobGraph).wait();

	entityMngr.RunCommands();
}

std::string World::DumpUpdateJobGraph() {
	return jobGraph.dump();
}

void World::AddCommand(const std::function<void()>& command) {
	entityMngr.AddCommand(command);
}

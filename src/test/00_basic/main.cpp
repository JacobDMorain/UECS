#include <UECS/World.h>

using namespace Ubpa::UECS;

struct Position { float val; };
struct Velocity { float val; };

struct MoverSystem {
	static void OnUpdate(Schedule& schedule) {
		schedule.RegisterEntityJob(
			[](const Velocity* v, Position* p) {
				p->val += v->val;
			},
			"Mover"
		);
	}
};

int main() {
	World w;
	w.systemMngr.RegisterAndActivate<MoverSystem>();
	w.entityMngr.Create<Position, Velocity>();
	w.Update();
}

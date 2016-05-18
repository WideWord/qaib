#pragma once

#include <qaib/game/Movable.hpp>
#include <qaib/game/Damagable.hpp>
#include <qaib/game/PawnController.hpp>
#include <qaib/util/Typedef.hpp>

#include <memory>
#include <Box2D/Dynamics/b2Body.h>

namespace qaib {
	
	class PawnController;
	class GameWorld;

	class Pawn: public Movable, public Damagable {
	private:
		Ref<PawnController> controller;
		float moveSpeed;

		b2Body* physicsBody;

		bool shootAllowed;
		float lastShootTimer;
		float shootTimeout;

		float health;

		float rotation;
	protected:
		friend class GameWorld;
		explicit Pawn(b2Body* physicsBody);
	public:

		b2Body* getPhysicsBody() {
			return physicsBody;
		}

		template<typename C, typename ... Args> void useController(Args& ... args) {
			controller = Ref<PawnController>(new C(args...));
			controller->setPawn(this);
		};

		void doTick(GameWorld& gameWorld, float deltaTime);

		bool isDead() {
			return health < 0;
		}

		virtual glm::vec2 getPosition() const override;
		virtual void setPosition(const glm::vec2& pos) override;

		virtual float getRotation() const override;
		virtual void setRotation(float rot) override;

		virtual void applyDamage(float damage) override;

		virtual ~Pawn();
	};

}
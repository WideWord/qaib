#pragma once

#include <qaib/game/Movable.hpp>
#include <qaib/game/Damagable.hpp>
#include <qaib/game/PawnController.hpp>
#include <qaib/util/Typedef.hpp>

#include <memory>
#include <queue>
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

		float score;

		glm::vec2 speed;
		std::queue<glm::vec2> speedFrames;
	protected:
		friend class GameWorld;
		explicit Pawn(b2Body* physicsBody);
	public:

		inline glm::vec2 getSpeed() {
			return speed;
		}

		b2Body* getPhysicsBody() {
			return physicsBody;
		}

		template<typename C, typename ... Args> void useController(Args& ... args) {
			controller = Ref<PawnController>(new C(args...));
			controller->setPawn(this);
		};

		void doTick(GameWorld& gameWorld, float deltaTime);

		inline bool isDead() const {
			return health <= 0;
		}

		inline float getHealth() const {
			return health;
		}

		inline float getInitialHealth() const {
			return 100;
		}

		inline float getScore() const {
			return score;
		}

		inline void addScore(float delta) {
			score += delta;
		}



		virtual glm::vec2 getPosition() const override;
		virtual void setPosition(const glm::vec2& pos) override;

		virtual float getRotation() const override;
		virtual void setRotation(float rot) override;

		virtual void applyDamage(float damage) override;

		virtual ~Pawn();
	};

}
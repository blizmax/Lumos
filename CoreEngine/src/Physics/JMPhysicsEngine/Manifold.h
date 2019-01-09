#pragma once

#include "JM.h"
#include "PhysicsObject3D.h"
#include "Maths/Maths.h"

namespace jm
{
	/* A contact constraint is actually the summation of a normal distance constraint
	along with two friction constraints going along the axes perpendicular to the collision
	normal.
	*/
	struct JM_EXPORT ContactPoint
	{
		float   sumImpulseContact;
		float	sumImpulseFriction;
		float	elatisity_term;
		float	collisionPenetration;

		maths::Vector3 collisionNormal;
		maths::Vector3 relPosA;			//Position relative to objectA
		maths::Vector3 relPosB;			//Position relative to objectB
	};

	class JM_EXPORT Manifold
	{
	public:
		Manifold();
		~Manifold();

		//Initiate for collision pair
		void Initiate(PhysicsObject3D* nodeA, PhysicsObject3D* nodeB);

		//Called whenever a new collision contact between A & B are found
		void AddContact(const maths::Vector3& globalOnA, const maths::Vector3& globalOnB, const maths::Vector3& _normal, const float& _penetration);

		//Sequentially solves each contact constraint
		void ApplyImpulse();
		void PreSolverStep(float dt);

		//Debug draws the manifold surface area
		void DebugDraw() const;

		//Get the physics objects
		PhysicsObject3D* NodeA() const { return m_pNodeA; }
		PhysicsObject3D* NodeB() const { return m_pNodeB; }
	protected:
		void SolveContactPoint(ContactPoint& c) const;
		void UpdateConstraint(ContactPoint& c);

	protected:
		PhysicsObject3D*			m_pNodeA;
		PhysicsObject3D*			m_pNodeB;
		std::vector<ContactPoint>	m_vContacts;
	};
}

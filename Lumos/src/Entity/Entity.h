#pragma once

#include "LM.h"
#include "Component/Components.h"

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

namespace Lumos
{
	class LUMOS_EXPORT Entity
	{
	protected:
		std::unordered_map<ComponentType, std::unique_ptr<LumosComponent>, EnumClassHash> m_Components;
	public:
		explicit Entity(const String& name = "");
		virtual ~Entity();

		template<typename T, typename... Args>
		void AddComponent(Args&&... args);

		template <typename T>
		/*const */T* GetComponent() const
		{
			return GetComponentInternal<T>();
		}

		template <typename T>
		T* GetComponent()
		{
			return static_cast<T*>(GetComponentInternal<T>());
		}

		void OnRenderObject();
		virtual void OnUpdateObject(float dt);
		virtual void OnIMGUI();
		virtual void OnGuizmo(uint mode = 0);
		virtual void Init();

		std::vector<std::shared_ptr<Entity>>& GetChildren() { return m_vpChildren; }
		void AddChildObject(std::shared_ptr<Entity>& child);

		void  SetBoundingRadius(float radius) { m_BoundingRadius = radius; }
		float GetBoundingRadius() const { return m_BoundingRadius; }

		uint& GetFrustumCullFlags() { return m_FrustumCullFlags; }

		void DebugDraw(uint64 debugFlags);

		TransformComponent* GetTransformComponent();

		void SetParent(Entity* parent);

		const String& GetName() const { return m_Name; }
		const String& GetUUID() const { return m_UUID; }

		const bool Active() const { return m_Active; }
		const bool ActiveInHierarchy() const;
		void SetActive(bool active) { m_Active = active; };
		void SetActiveRecursive(bool active);

	private:

		Entity(Entity const&) = delete;
		Entity& operator=(Entity const&) = delete;

		void AddComponent(std::unique_ptr<LumosComponent> component);

		template <typename T>
		T* GetComponentInternal() const
		{
			ComponentType type = T::GetStaticType();
			auto it = m_Components.find(type);
			if (it == m_Components.end())
				return nullptr;
			return static_cast<T*>(it->second.get());
		}

		String					m_Name;
		Entity*					m_pParent;
		std::vector<std::shared_ptr<Entity>> m_vpChildren;
		float					m_BoundingRadius;
		uint					m_FrustumCullFlags;
		String                  m_UUID;
		bool					m_Active;
		TransformComponent*		m_DefaultTransformComponent = nullptr;
	};

	template<typename T, typename ... Args>
	inline void Entity::AddComponent(Args && ...args)
	{
		std::unique_ptr<T> component(new T(std::forward<Args>(args) ...));
		AddComponent(std::move(component));
	}
}

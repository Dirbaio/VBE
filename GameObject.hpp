#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "tools.hpp"

class Game;
class GameObject { //scenegraph nodes
	public:
		GameObject();
		virtual ~GameObject();

		static GameObject* getObjectByName(std::string name);
		static GameObject* getObjectByID(int id);

		virtual void update(float deltaTime);
		virtual void draw() const;

		void addObject(GameObject* object);
		void removeFromParent();
		void setName(std::string newName);
		void setDrawPriority(int newPriority);
		void setUpdatePriority(int newPriority);
		std::string getName();
		int getDrawPriority();
		int getUpdatePriority();

		template<class T>
		void getAllObjectsOfType(std::vector<T*> &v) {
			T* p = dynamic_cast<T*>(this);
			if(p) v.push_back(p);
			for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
				(*it)->getAllObjectsOfType<T>(v);
		}

		template<class T>
		T* getFirstObjectOfType() {
			T* p = dynamic_cast<T*>(this);
			if(p) return p;
			for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it) {
				p = (*it)->getFirstObjectOfType<T>();
				if(p) return p;
			}
			return NULL;
		}

		const int id;
		bool isAlive;
	protected:
		virtual void onObjectAdd(GameObject* object);

		GameObject* parent;
		std::list<GameObject*> children;
		mat4f transform;
		mat4f fullTransform;
		Game* game;
	private:
		void calcFullTransform(mat4f parentFullTransform);
		int drawPriority;
		int updatePriority;
		std::string name;

		friend class Game;

	public:
		// debug function. Checks all nodes are childs of their parents (only once)
		// and that not more than one null parent exists (the root object)
		static bool checkTree(GameObject* root, int& nulls);

};

#endif // GAMEOBJECT_HPP

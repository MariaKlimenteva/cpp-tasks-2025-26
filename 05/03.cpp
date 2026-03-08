#include <print>
#include <vector>
#include <string>
#include <algorithm>

class GameObject
{
public:
    virtual ~GameObject() = default;

    void update() 
    {
        initialize();
        execute();
        finalize();
    }

protected:
    virtual void initialize() const { std::print("GameObject init\n"); }
    virtual void execute() = 0;
    virtual void finalize() const { std::print("GameObject finalize\n"); }
};

class Unit : public GameObject
{
public:
    explicit Unit(std::string name) : m_name(std::move(name)) {}

protected:
    void execute() override
    {
        std::print("Unit {} acting.\n", m_name);
    }

private:
    std::string m_name;
};

class Squad : public GameObject
{
public:
    void add(GameObject* obj)
    {
        m_children.push_back(obj);
    }

    ~Squad() override
    {
        for(auto* child : m_children) delete child;
    }

protected:
    void execute() override
    {
        std::print("Squad commanding:\n");
        for(auto* child : m_children)
        {
            child->update();
        }
    }

private:
    std::vector<GameObject*> m_children;
};

class GameBuilder
{
public:
    GameBuilder() { reset(); }
    
    ~GameBuilder() { delete m_squad; }

    void reset()
    {
        m_squad = new Squad();
    }

    void build_unit(const std::string& name)
    {
        m_squad->add(new Unit(name));
    }

    GameObject* get_result()
    {
        GameObject* result = m_squad;
        m_squad = nullptr;
        return result;
    }

private:
    Squad* m_squad = nullptr;
};

int main()
{
    GameBuilder builder;
    
    builder.build_unit("Archer");
    builder.build_unit("Knight");
    
    GameObject* army = builder.get_result();
    
    army->update();
    
    delete army;
}
// g++ -std=c++23 03.cpp -o 03
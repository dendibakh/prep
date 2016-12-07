#include <gtest/gtest.h>
#include <initializer_list>
#include <tuple>
#include <vector>
#include <iostream>
#include <functional>
#include <memory>

using actFunc = std::function<void()>;
using checkFunc = std::function<bool(bool)>;
using fallFunc = std::function<void()>;

class IAction
{
public:
  virtual ~IAction() = default;
  virtual void act() = 0;
  virtual bool check(bool) = 0;
  virtual void fall() = 0;
  virtual bool isIface() = 0;
};

class SimpleAction : public IAction
{
public:
  SimpleAction(actFunc func) : func(func) {}
  void act() override {func();}
  bool check(bool) override {return true;}
  void fall() override {}
  bool isIface() override {return false;}
private:
  actFunc func;
};

class InterfaceAction : public IAction
{
public:
  InterfaceAction (actFunc fact, checkFunc fcheck, fallFunc ffall) :
    fact(fact), fcheck(fcheck), ffall(ffall) {}
  void act() override {fact();}
  bool check(bool p) override {return fcheck(p);}
  void fall() override {ffall();}
  bool isIface() override {return true;}
private:
  actFunc fact;
  checkFunc fcheck;
  fallFunc ffall;
};

struct Opers
{
    template <typename... T>
    Opers(T&&... t)
    {
        (void)std::initializer_list<int>{(table.emplace_back(std::forward<T>(t)), 0)...};
    }
    void run()
    {
        if (table.empty())
          return;
        cur = table.begin();      

        (*cur)->act();
        while (!(*cur)->isIface())
        {
          cur++;
          if (cur != table.end()) 
            (*cur)->act();
          else
            break;
        }
    }
    void cont(bool p)
    {
        if (done()) 
          return;

        if ((*cur)->check(p))
        {
            cur++;
            if (cur != table.end()) 
            {
              (*cur)->act();
              while (!(*cur)->isIface())
              {
                cur++;
                if (cur != table.end()) 
                  (*cur)->act();
               else
                  break;
              }
            }
        }
        else
        {
            (*cur)->fall();
            cur = table.end();
        }
    }
    bool done() { return cur == table.end(); }
    using Table = std::vector<std::unique_ptr<IAction>>;
    Table table;
    Table::iterator cur;
};

TEST(xxx, 1)
{
  	int x = 1;
	Opers opers(std::make_unique<InterfaceAction>([&x]{++x;},	[](bool p){return p && true;}, 	[]{std::cout << "step 1 failed\n";}),
		    std::make_unique<InterfaceAction>([&x]{x*=2;},	[](bool p){return p && true;},  []{std::cout << "step 2 failed\n";}),
		    std::make_unique<InterfaceAction>([&x]{--x;},	[](bool p){return p && true;}, 	[]{std::cout << "step 3 failed\n";}));
	opers.run();
	EXPECT_EQ(2, x);
	opers.cont(true);
	EXPECT_EQ(4, x);
	opers.cont(true);
	EXPECT_EQ(3, x);
	opers.cont(true);
}

TEST(xxx, 2)
{
	int x = 1;
	Opers opers(std::make_unique<InterfaceAction>([&x]{++x;},	[](bool p){return p && true;}, 	[]{std::cout << "step 1 failed\n";}),
		    std::make_unique<InterfaceAction>([&x]{x*=2;},	[](bool p){return p && true;},  []{std::cout << "step 2 failed\n";}),
		    std::make_unique<InterfaceAction>([&x]{--x;},	[](bool p){return p && false;}, []{std::cout << "step 3 failed\n";}));
	opers.run();
	while(!opers.done())
		opers.cont(true);

	opers.cont(true);
	EXPECT_EQ(3, x);
}

TEST(xxx, 3)
{
	int x = 1;
	Opers opers(std::make_unique<InterfaceAction>([&x]{++x;},	[](bool p){return p && true;}, 	[]{std::cout << "step 1 failed\n";}),
		    std::make_unique<InterfaceAction>([&x]{x*=2;},	[](bool p){return p && true;},  []{std::cout << "step 2 failed\n";}),
		    std::make_unique<SimpleAction>   ([&x]{x*=2;}),
		    std::make_unique<InterfaceAction>([&x]{--x;},	[](bool p){return p && false;}, []{std::cout << "step 3 failed\n";}));
	opers.run();
	while(!opers.done())
		opers.cont(true);

	opers.cont(true);
	EXPECT_EQ(7, x);
}



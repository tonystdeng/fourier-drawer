#include "view.hpp"
#include "compile.hpp"


int main(int argc, char *argv[])
{

    if (!(argc==3))
    {
        std::cout<<"Expected two arguments, received "<<argc-1<<"\n";
        return 1;
    }

    if (*argv[1]=='c')
    {
        return compile(argv[2],200);
    }else if (*argv[1]=='o')
    {
        Game game(argv[2]);

        while (game.window->isOpen()){
            game.main();
        }
    }else
    {
        std::cout<<"First augument can only be either \"c\" for compile and \"o\" for open\n";
        return 1;
    }
    return 0;
}
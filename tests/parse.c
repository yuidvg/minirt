#include "../includes/parse.h"

int main(int argc, char **argv)
{
    t_scene scene;

    if (argc != 2)
        return (1);
    init_scene(argv[1], &scene);
}
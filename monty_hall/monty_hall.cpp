
// Monty Hall paradox simulation and verification
// (C) 2018  Oleksandr Dunaievskyi  <od@xyzw.me>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include <array>
#include <cstdio>
using Conf = std::array<bool, 3>;



Conf  generate_random_conf()
{
    static Conf config[]=
    {
        {1, 0, 0}, // 1=car, 0=goat
        {0, 1, 0},
        {0, 0, 1}
    };

    return config[rand()%(sizeof(config)/sizeof(Conf))];
}


int main()
{
    srand(0);

    // no switch, always pick 1 door
    int wins = 0;
    for (int i = 0; i < 1000; ++i)
    {
        auto conf = generate_random_conf();
        if (conf[0]) // car?
        {
            ++wins;
        }
    }
    printf("prob of winning if not switching is %f\n", (float)wins / 1000);


    // check the door with the goat (never 1 as we choose it initially), then switch from door 1 to the third remaining door
    wins = 0;
    for (int i = 0; i < 1000; ++i)
    {
        auto conf = generate_random_conf();
        if (conf[1] == 0) // goat?
        {
            if (conf[2]) // car?
            {
                ++wins;
                continue;
            }
        }

        if (conf[2] == 0)
        {
            if (conf[1])
            {
                ++wins;
                continue;
            }
        }
    }
    printf("prob of winning if switching is %f\n", (float)wins / 1000);

    return 0;
}

#include <iostream>

using namespace std;

extern "C" {
  void display ()
  {
    cout << "-----------------------------------------------------" << endl;
    cout << "The darkest nights give birth to the brightest stars" << '\n';
    cout << "-----------------------------------------------------" << endl;

    int dom [][10]={ {0,0,0,0,1,2,0,0,0,0},
                     {0,0,0,1,0,0,2,0,0,0},
                     {0,0,1,0,0,0,0,2,0,0},
                     {0,1,3,3,3,3,3,3,2,0},
                     {1,0,4,0,0,0,0,4,0,2},
                     {0,0,4,0,0,0,0,4,0,0},
                     {0,0,4,0,0,0,0,4,0,0},
                     {0,0,4,0,0,0,0,4,0,0},
                     {0,0,4,0,0,0,0,4,0,0},
                     {0,0,4,5,5,5,5,4,0,0},
                   };
    char symbol [6]= {' ','(',')' ,'-','|','_'};

    for (int i = 0; i < 10; i++){
      for (int j = 0; j < 10; j++){
        switch (dom[i][j]){
          case 0: cout << symbol[0]; continue;
          case 1: cout << symbol[1]; continue;
          case 2: cout << symbol[2]; continue;
          case 3: cout << symbol[3]; continue;
          case 4: cout << symbol[4]; continue;
          case 5: cout << symbol[5]; continue;
        }
      }
      cout << endl;
    }
  }
}

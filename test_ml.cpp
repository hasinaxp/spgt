#include <iostream>
#include "spgt/sp_ml.hpp"

using namespace std;
using namespace sp;

int main(int argc, char ** argv)
{
  printf("sp_ml.hpp test\n");


  f32 data[] = {0.0f, 0.0, 0.0, 0.1, 1.0, 0.0, 1.0, 1.0};
  u32 ndata = sizeof(data) / sizeof(f32);

  input_layer inp(2);
  dense_layer l1(3);
  l1.connect(&inp);
  dense_layer l2(1);
  l2.connect(&l1);

  model nn(&inp, &l2);
  auto preds = nn.predict(data, ndata);

  for(auto & m : preds)
    cout << m << endl;


}

#include "block.h"

Block::Block(){
  Init();
}

void Block::Init(){
  Master = false;
  Solve1 = false;
  Solve2 = false;
}

void Block::Barier(int ThreadID){
  if (ThreadID == 0) Master = true;
  if (ThreadID == 1) Solve1 = true;
  if (ThreadID == 2) Solve2 = true;
  while (!Master && !Solve1 && !Solve2);
}

void Block::MasterBarier(){
  while (!Solve1 && !Solve2);
}

Block::~Block(){

}

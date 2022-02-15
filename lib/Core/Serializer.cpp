//
// Created by pseudo on 10/27/21.
//

#include "Serializer.h"
#include "llvm/IR/Function.h"
#include <fstream>
#include <iostream>

void Serializer::addTrainingTuple(const std::vector<llvm::Instruction *> instructions,
                                  bool feasible) {
  trainingData.push_back(PathTuple(instructions, feasible));
}

void Serializer::dumpInstructions(const std::vector<llvm::Instruction*> path,
                                  std::ofstream &output) {
  output << path.size() << "\n";
  for (llvm::Instruction *i : path) {
    output << getCanonicalName(i) << ";;";
  }
  output << "\n";
}

std::string Serializer::getCanonicalName(const llvm::Instruction *instruction) {
  /*
   * Returns the canonical name for the given instruction to uniquely identify
   * it outside of the llvm ecosystem. This could be done better by doing it
   * once for every instruction instead of searching for the indexes for every
   * instruction
   */
  const llvm::BasicBlock *basicBlock = instruction->getParent();
  const llvm::Function *function = basicBlock->getParent();
  std::string funcName = function->getName().str();
  int bbIdx = -1, insIdx = -1;
  int i = 0;

  // find the index of basic block within the function
  for (auto it = function->begin(); it != function->end(); it++, i++) {
    const llvm::BasicBlock *bb = &*it;
    if (bb == basicBlock) {
      bbIdx = i;
    }
  }

  i = 0;
  // find the index of instruction within basic block
  for (auto it = basicBlock->begin(); it != basicBlock->end(); it++, i++) {
    const llvm::Instruction *ins = &*it;
    if (ins == instruction) {
      insIdx = i;
    }
  }

  std::stringstream canonicalName;
  canonicalName << funcName << "-" << bbIdx << "-" << insIdx;
  return canonicalName.str();
}

void Serializer::dumpTrainingData(const std::string &filename) {

  std::cout << "Dumping Data" << std::endl;
  std::ofstream output;
  output.open("training.data");

  for (auto tuple : trainingData) {

    output << tuple.feasible << "\n";
    dumpInstructions(tuple.instructions, output);
  }
  output.close();
}

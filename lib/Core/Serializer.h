#include "ExecutionState.h"
#include "klee/Module/KModule.h"
#include <string>
//
// Created by pseudo on 10/27/21.
//

#ifndef KLEE_SERIALIZER_H
#define KLEE_SERIALIZER_H

struct PathTuple {
  std::vector<llvm::Instruction *> instructions;
  bool feasible;

  PathTuple(const std::vector<llvm::Instruction *> instructions, bool feasible) {
    this->instructions = instructions;
    this->feasible = feasible;
  }
};

class Serializer {

  std::vector<PathTuple> trainingData;

public:
  // add a training tuple

  void addTrainingTuple(const std::vector<llvm::Instruction*> instructions,
                        bool feasible);
  // dump the instruction trace
  void dumpInstructions(const std::vector<llvm::Instruction*> path,
                        std::ofstream &output);

  // dumps the training data into a file
  void dumpTrainingData(const std::string &filename);

  // get the canonical name for the instruction
  std::string getCanonicalName(const llvm::Instruction *instruction);
};

#endif // KLEE_SERIALIZER_H

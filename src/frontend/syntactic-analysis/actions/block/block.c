#include "block.h"

// Block
Block* EmptyBlockGrammarAction() {
	LogDebug("[Bison] EmptyBlockGrammarAction");
	Block* block = calloc(1, sizeof(Block));
	AssertNotNullCallback(block, HandleOutOfMemoryError);
	block->type = EMPTY_BLOCK;
	return block;
}

Block* InstructionsBlockGrammarAction(Instructions* instructions) {
	LogDebug("[Bison] InstructionsBlockGrammarAction");
	Block* block = calloc(1, sizeof(Block));
	AssertNotNullCallback(block, HandleOutOfMemoryError);
	block->type = INSTRUCTIONS_BLOCK;
	block->instructions = instructions;
	return block;
}

Block* InstructionsBlockBlockGrammarAction(Instructions* instructions, Block* block) {
	LogDebug("[Bison] InstructionsBlockBlockGrammarAction");
	Block* newBlock = calloc(1, sizeof(Block));
	AssertNotNullCallback(newBlock, HandleOutOfMemoryError);
	newBlock->type = RECURSIVE_BLOCK;
	newBlock->instructions = instructions;
	newBlock->block = block;
	return newBlock;
}

Block* InstructionsBlockBlockInstructionsGrammarAction(Instructions* instructions, Block* block, Instructions* bottomInstructions) {
	LogDebug("[Bison] InstructionsBlockBlockInstructionsGrammarAction");
	Block* newBlock = calloc(1, sizeof(Block));
	AssertNotNullCallback(newBlock, HandleOutOfMemoryError);
	newBlock->type = INSTRUCTIONS_BLOCK_INSTRUCTIONS;
	newBlock->instructions = instructions;
	newBlock->block = block;
	newBlock->bottomInstructions = bottomInstructions;
	return newBlock;
}

#include <stdint.h>
#include <stdio.h>

// Initialize an empty 64-bit bitboard
uint64_t bitboard = 0;

uint64_t getBitboard (){
  return bitboard;
}

// Function to set a piece at a specific position (0-63)
void setPiece(int position) { bitboard |= (1ULL << position); }

// Function to check if a piece exists at a specific position
int isPieceAt(int position) { return (bitboard & (1ULL << position)) != 0; }

// Function to clear a piece at a specific position
void clearPiece(int position) { bitboard &= ~(1ULL << position); }

// Function to print the bitboard in binary format
void printBitboard() {
  for (int i = 63; i >= 0; i--) {
    printf("%d", (bitboard & (1ULL << i)) ? 1 : 0);
    if (i % 8 == 0)
      printf(" "); // Add a space every 8 bits for readability
  }
  printf("\n");
}

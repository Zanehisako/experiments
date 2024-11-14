
#include <stdint.h>
#include <stdio.h>

// Initialize an empty 64-bit bitboard
uint64_t white_bitboard = 0;
uint64_t black_bitboard = 0;

uint64_t getWhiteBitboard() { return white_bitboard; }
uint64_t getBlackBitboard() { return black_bitboard; }

// Function to set a piece at a specific position (0-63)
void setWhitePiece(int position) { white_bitboard |= (1ULL << position); }
void setBlackPiece(int position) { black_bitboard |= (1ULL << position); }

// Function to check if a piece exists at a specific position
int isWhitePieceAt(int position) {
  return (white_bitboard & (1ULL << position)) != 0;
}

int isBlackPieceAt(int position) {
  return (black_bitboard & (1ULL << position)) != 0;
}

// Function to clear a piece at a specific position
void clearWhitePiece(int position) { white_bitboard &= ~(1ULL << position); }
void clearBlackPiece(int position) { black_bitboard &= ~(1ULL << position); }

// Function to print the bitboard in binary format
void printWhiteBitboard() {
  for (int i = 63; i >= 0; i--) {
    printf("%d", (white_bitboard & (1ULL << i)) ? 1 : 0);
    if (i % 8 == 0)
      printf(" "); // Add a space every 8 bits for readability
  }
  printf("\n");
}

void printBlackBitboard() {
  for (int i = 63; i >= 0; i--) {
    printf("%d", (black_bitboard & (1ULL << i)) ? 1 : 0);
    if (i % 8 == 0)
      printf(" "); // Add a space every 8 bits for readability
  }
  printf("\n");
}

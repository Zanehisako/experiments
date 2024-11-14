// Load the WebAssembly module
BitboardModule().then((Module) => {
  // Once the module is loaded, you can use the C functions

  // Initialize the bitboard
  Module._setWhitePiece(3);
  console.log("Bitboard after setting position 3:", Module._getWhiteBitboard());

  // Check if there's a piece at position 3
  const isPiece = Module._isWhitePieceAt(3);
  console.log("Is there a piece at position 3?", isPiece ? "Yes" : "No");

  // Clear the piece at position 3
  Module._clearWhitePiece(3);
  Module._setBlackPiece(63);

  console.log("Bitboard after setting position 3:", Module._getBlackBitboard());
  Module._printWhiteBitboard();
  Module._printBlackBitboard();
});

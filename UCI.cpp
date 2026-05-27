#include "uci.h"

Move parseMoveString(const Board& board, const std::string& moveStr) {
    int fromFile = moveStr[0] - 'a';
    int fromRank = moveStr[1] - '1';
    int toFile   = moveStr[2] - 'a';
    int toRank   = moveStr[3] - '1';

    int from = squareIndex(fromFile, fromRank);
    int to   = squareIndex(toFile,   toRank);

    PieceType promotion = NONE;
    if (moveStr.size() == 5) {
        switch (moveStr[4]) {
            case 'q': promotion = QUEEN;  break;
            case 'r': promotion = ROOK;   break;
            case 'b': promotion = BISHOP; break;
            case 'n': promotion = KNIGHT; break;
        }
    }

    Move move;
    move.from      = from;
    move.to        = to;
    move.promotion = promotion;
    return move;
}
// Wandelt einen Zugstring in einen Moven um

void applyMovesFromString(Board& board, const std::string& movesStr) {
    std::istringstream ss(movesStr);
    std::string token;

    while (ss >> token) {
        if (token == "moves") continue;
        Move move = parseMoveString(board, token);
        applyMove(board, move);
    }
}
// Wendet eine ganze Reihe von Zügen auf das Brett an

    Board parsePosition(const std::string& line) {
        Board board;
        setupStartPosition(board);

        size_t movesPos = line.find("moves");
        if (movesPos == std::string::npos)
            return board;

        std::istringstream ss(line.substr(movesPos + 6));
        std::string token;

        while (ss >> token) {
            if (token.size() < 4) continue;  // Ungültige Züge überspringen

            int fromFile = token[0] - 'a';
            int fromRank = token[1] - '1';
            int toFile   = token[2] - 'a';
            int toRank   = token[3] - '1';

            // Bounds check
            if (fromFile < 0 || fromFile > 7 || fromRank < 0 || fromRank > 7 ||
                toFile   < 0 || toFile   > 7 || toRank   < 0 || toRank   > 7)
                continue;

            Move move;
            move.from      = squareIndex(fromFile, fromRank);
            move.to        = squareIndex(toFile,   toRank);
            move.promotion = NONE;

            if (token.size() == 5) {
                switch (token[4]) {
                    case 'q': move.promotion = QUEEN;  break;
                    case 'r': move.promotion = ROOK;   break;
                    case 'b': move.promotion = BISHOP; break;
                    case 'n': move.promotion = KNIGHT; break;
                }
            }

            applyMove(board, move);
        }

        return board;
    }   
// Liest die Position aus dem UCI 

std::string moveToString(const Move& move) {
    char files[] = "abcdefgh";
    std::string result = "";

    result += files[move.from % 8];
    result += (char)('1' + (move.from / 8));
    result += files[move.to % 8];
    result += (char)('1' + (move.to / 8));

    if (move.promotion != NONE) {
        switch (move.promotion) {
            case QUEEN:  result += 'q'; break;
            case ROOK:   result += 'r'; break;
            case BISHOP: result += 'b'; break;
            case KNIGHT: result += 'n'; break;
            default: break;
        }
    }

    return result;
}
// Wandelt einen Move zurück in Text 

void uciLoop() {
    std::cout << "id name WeirdChessEngine\n";
    std::cout << "id author Leon Eltscher\n";
    std::cout << "uciok\n";
    std::cout.flush();

    std::string line;
    Board board;
    setupStartPosition(board);
    std::vector<std::string> playedMoves;

    while (std::getline(std::cin, line)) {
// UCI-Befehle lesen und verarbeiten
        if (line == "uci") {
            std::cout << "id name WeirdChessEngine\n";
            std::cout << "id author Du\n";
            std::cout << "uciok\n";
            std::cout.flush();
        }
// UCI-Initialisierung

        else if (line == "isready") {
            std::cout << "readyok\n";
            std::cout.flush();
        }
// UCI-Bereitschaftsprüfung

        else if (line.substr(0, 8) == "position") {
            board = parsePosition(line);
            // Sicherstellen dass sideToMove korrekt ist
            if (line.find("moves") == std::string::npos)
                board.sideToMove = WHITE;
        }
// UCI-Position setzen

        else if (line.substr(0, 2) == "go") {
    SearchResult result = findBestMove(board, 4);
    std::string move = moveToString(result.bestMove);
    std::cerr << "DEBUG: [" << move << "] len=" << move.size() << "\n";
    std::cout << "bestmove " << move << "\n";
    std::cout.flush();
}
// UCI-Suchbefehl

        else if (line == "quit") {
            break;
        }
    }
}
// GUI beendet


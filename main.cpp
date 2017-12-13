#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

#ifdef _WIN32
#define DS '\\'
#define FFMPEG_COMMAND "ffmpeg.exe"
#define PAUSE_CALL "pause"
#else
#define DS '/'
#define FFMPEG_COMMAND "ffmpeg"
#define PAUSE_CALL "read"
#endif

std::string basename(const std::string &file);

void convertMP3(const std::string &file, uint16_t bitrate);

void error(const std::string &msg);

std::string extension(const std::string &file);

std::string fileName(const std::string &file);

std::string basename(const std::string &file) {
    return file.substr(0, file.rfind('.'));
}

void convertMP3(const std::string &file, uint16_t bitrate) {
    std::string ffmpeg(FFMPEG_COMMAND);
    std::string br(std::to_string(bitrate) + "k");
    std::string outfile(basename(file) + ".mp3");
    std::string command(
            ffmpeg + " -y -loglevel panic -i \"" + file + "\" -ab " + br + " -map_metadata 0 -id3v2_version 3 \"" +
            outfile + "\"");
    std::system(command.c_str());
}

void error(const std::string &msg) {
    std::cerr << "Error: " << msg << std::endl;
    system(PAUSE_CALL);
    exit(0);
}

std::string extension(const std::string &file) {
    return file.substr(file.rfind('.') + 1);
}

std::string fileName(const std::string &file) {
    return file.substr(file.rfind(DS) + 1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        error("No input files.");
    }

    std::setfill(' ');

    std::cout << "------------------------------------------------------------" << std::endl;

    std::cout << "| mp3convert 1.0.2 |" << std::setw(39 - static_cast<uint8_t>(floor(log((argc - 1))) + 1))
              << "| Amount: "
              << (argc - 1) << "|" << std::endl;

    std::cout << "------------------------------------------------------------" << std::endl;

    std::cout << "| Bitrate? For example: 128 to encode MP3 in 128 kbps.     |";

    uint16_t bitrate = 0;
    std::cin >> bitrate;

    std::cout << "\r";

    for (int i = 1; i < argc; ++i) {
        std::string file(argv[i]);
        std::string fileCanonical(fileName(file).substr(0, 30));

        if (extension(file) != "mp3") {
            std::cout << "| Converting: " << fileCanonical;
        } else {
            std::cout << "| Skipping:   " << fileCanonical;
        }

        std::cout
                << std::setw(
                        static_cast<int>(32 - fileCanonical.length() -
                                         static_cast<uint8_t>(floor(log((argc - 1))) + 1) + floor(log((i))) +
                                         1)) << " [" << i << "/" << (argc - 1)
                << "]|" << std::endl;

        if (extension(file) != "mp3") {
            convertMP3(file, bitrate);
        }
    }

    return 0;
}

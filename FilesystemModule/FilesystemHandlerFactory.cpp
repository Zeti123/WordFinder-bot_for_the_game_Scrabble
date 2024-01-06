#include "FilesystemHandlerFactory.hpp"

#include "FilesystemHandler.hpp"
#include "FileReader.hpp"
#include "LanguageHandler.hpp"

std::unique_ptr<IFilesystemHandler> FilesystemHandlerFactory::create()
{
    return std::make_unique<FilesystemHandler>(std::make_unique<LanguageHandler>(), std::make_unique<FileReader>());
}

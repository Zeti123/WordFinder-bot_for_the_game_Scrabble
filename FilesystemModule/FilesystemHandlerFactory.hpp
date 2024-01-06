#pragma once

#include "IFilesystemHandler.hpp"

class FilesystemHandlerFactory
{
public:
    std::unique_ptr<IFilesystemHandler> create();
};

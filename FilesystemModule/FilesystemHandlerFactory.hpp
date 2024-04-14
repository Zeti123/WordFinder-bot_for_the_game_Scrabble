#pragma once

#include "IFilesystemHandler.hpp"

#include <memory>

class FilesystemHandlerFactory
{
public:
    static std::unique_ptr<IFilesystemHandler> create();
};

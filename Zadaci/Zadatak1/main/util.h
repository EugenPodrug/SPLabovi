#pragma once

/// <summary>
/// Set the current directory to be the same as the executable directory.
/// </summary>
/// <returns>If the function succeeds, the return value is nonzero. If the function fails, the return value is zero.</returns>
int FixupCurrentDirectory();
#pragma once

#include "UniDxDefine.h"
#include "Debug.h"

#include "GameObject.h"
#include "Transform.h"
#include "GameObject_impl.h"

namespace UniDx
{

using Microsoft::WRL::ComPtr;

std::string ToUtf8(const wstring& wstr);
wstring ToUtf16(const std::string str);

}

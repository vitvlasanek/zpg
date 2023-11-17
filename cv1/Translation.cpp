#include "Translation.h"

mat4 Translation::GetMatrix() const
{
    return glm::translate(glm::mat4(1.0f), translation_);
}

Translation::Translation(vec3 translation): translation_(translation)
{
}

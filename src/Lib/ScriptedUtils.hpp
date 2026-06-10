#pragma once

template<typename T>
T* GetScriptedPropertyPtr(RED4ext::ISerializable& aInstance, const char* aName)
{
    return aInstance.GetType()->GetProperty(aName)->GetValuePtr<T>(&aInstance);
}
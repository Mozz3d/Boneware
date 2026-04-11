#pragma once

namespace Native::anim
{
struct MetaExtraTrack
{
    RED4ext::CName m_name;
    float m_value;
};

struct MetaExtraTransform
{
    RED4ext::CName m_name;
    RED4ext::QsTransform m_value;
};

struct MetaPose
{
    RED4ext::DynArray<RED4ext::QsTransform> m_transforms;
    uint16_t m_numBones;
    RED4ext::DynArray<float> m_tracks;
    RED4ext::DynArray<MetaExtraTrack> m_extraTracks;
    RED4ext::DynArray<MetaExtraTransform> m_extraTransforms;
};
}

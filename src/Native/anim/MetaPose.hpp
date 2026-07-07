#pragma once

#include <RED4ext/Scripting/Natives/animMetaRig.hpp>

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

NATIVE_INFO(ntv::anim::MetaPose)
{
    NATIVE_MEMBER_FUNC(
    void ,ResetPartTransforms,(r4e::Span<r4e::QsTransform>&, uint32_t, const r4e::anim::MetaRig&), 3570868109);

    NATIVE_MEMBER_FUNC(
    r4e::QsTransform ,GetBoneMSTransform,(const r4e::anim::MetaRig&, uint32_t) const, 4074379797);

    NATIVE_MEMBER_FUNC(
    void ,CalcMS,(const r4e::anim::MetaRig&), 1343032985);
};

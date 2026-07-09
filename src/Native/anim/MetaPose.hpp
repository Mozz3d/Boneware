#pragma once

#include <Native/anim/MetaRig.hpp>

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
    void ResetTransforms(const r4e::Span<const r4e::QsTransform>& rigPoseLS, uint32_t partIndex, const r4e::anim::MetaRig& metaRig)
    {
        const auto& part = NTV_GET(metaRig,unkStructArray)[partIndex];
        for (const auto& map : r4e::Span(part.boneMappings.Data(), part.distanceCategoryBoneMapping[0]))
        {
            m_transforms[map.dst] = rigPoseLS[map.src];
        }
    }

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
    void ,ResetTransforms,(const r4e::Span<const r4e::QsTransform>&, uint32_t, const r4e::anim::MetaRig&), 3570868109);

    NATIVE_MEMBER_FUNC(
    r4e::QsTransform ,GetBoneMSTransform,(const r4e::anim::MetaRig&, uint32_t) const, 4074379797);

    NATIVE_MEMBER_FUNC(
    void ,CalcMS,(const r4e::anim::MetaRig&), 1343032985);
};

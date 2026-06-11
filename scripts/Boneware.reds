
public native struct BoneTransformEntry {
    public native let name: CName;
    public native let transform: QsTransform;
}

public native struct TrackValueEntry {
    public native let name: CName;
    public native let value: Float;
}

public native struct MetaPoseRef {
    public static native func GetTransforms(self: script_ref<MetaPoseRef>) -> array<QsTransform>
    public static native func GetTransform(self: script_ref<MetaPoseRef>, boneIndex: Int32) -> QsTransform
    public static native func GetTracks(self: script_ref<MetaPoseRef>) -> array<Float>
    public static native func GetTrack(self: script_ref<MetaPoseRef>, trackIndex: Int32) -> Float
}

public native struct MetaRigRef {
    public static native func GetBoneTransforms(self: script_ref<MetaRigRef>) -> array<QsTransform>
    public static native func GetBoneTransform(self: script_ref<MetaRigRef>, boneIndex: Uint32) -> QsTransform
    public static native func GetBoneNames(self: script_ref<MetaRigRef>) -> array<CName>
    public static native func GetBoneName(self: script_ref<MetaRigRef>, boneIndex: Int32) -> CName
    public static native func GetBoneIndex(self: script_ref<MetaRigRef>, boneName: CName) -> Int32

    public static native func GetTrackValues(self: script_ref<MetaRigRef>) -> array<Float>
    public static native func GetTrackValue(self: script_ref<MetaRigRef>, trackIndex: Uint32) -> Float
    public static native func GetTrackNames(self: script_ref<MetaRigRef>) -> array<CName>
    public static native func GetTrackName(self: script_ref<MetaRigRef>, trackIndex: Int32) -> CName
    public static native func GetTrackIndex(self: script_ref<MetaRigRef>, trackname: CName) -> Int32
}

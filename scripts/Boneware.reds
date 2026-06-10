
public native struct AdditiveTransformEntry {
    public native let name: CName;
    public native let transform: QsTransform;
}

public native struct MetaPoseRef {
    public static native func GetTransforms(self: script_ref<MetaPoseRef>) -> array<QsTransform>
    public static native func GetTracks(self: script_ref<MetaPoseRef>) -> array<Float>
}

public native struct MetaRigRef {
    public static native func GetBoneNames(self: script_ref<MetaRigRef>) -> array<CName>
}

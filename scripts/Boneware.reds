public native class BoneOffsetEntry {
    public native let name: CName;
    public native let transform: QsTransform;
}

public native class MetaPoseRef {
    public native func GetTransforms() -> array<QsTransform>
    public native func GetTracks() -> array<Float>
}

public native class MetaRigRef {
    public native func GetBonesNames() -> array<CName>
}

@if(ModuleExists("Codeware"))

@addField(AnimatedComponent)
private let metaPoseRef: MetaPoseRef;

@addMethod(AnimatedComponent)
public func GetMetaPose() -> MetaPoseRef {
    return this.metaPoseRef;
}

@addField(AnimatedComponent)
private let metaRigRef: MetaRigRef;

@addMethod(AnimatedComponent)
public func GetMetaRig() -> MetaRigRef {
    return this.metaRigRef;
}

@addField(AnimatedComponent)
private let persistentBoneOffsets: array<BoneOffsetEntry>;

@addMethod(AnimatedComponent)
public native func GetRig() -> ref<animRig>;


@addField(entISkinTargetComponent)
public let visualScale: Vector3;


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

@if(ModuleExists("Codeware"))

@addField(AnimatedComponent)
private let metaPoseRef: MetaPoseRef;

@addField(AnimatedComponent)
private let metaRigRef: MetaRigRef;

@addField(AnimatedComponent)
public let additiveTransforms: array<AdditiveTransformEntry>;

@addMethod(AnimatedComponent)
public native func GetRig() -> ref<animRig>;

@addMethod(AnimatedComponent)
public native func ForceReferencePose(force: Bool);

@addMethod(AnimatedComponent)
public func GetMetaPose() -> MetaPoseRef {
    return this.metaPoseRef;
}

@addMethod(AnimatedComponent)
public func GetMetaRig() -> MetaRigRef {
    return this.metaRigRef;
}

@addMethod(AnimatedComponent)
public func AddAdditiveTransform(name: CName, transform: script_ref<QsTransform>) {
    let entry = new AdditiveTransformEntry();
    entry.name = name;
    entry.transform = Deref(transform);
    ArrayPush(this.additiveTransforms, entry);
}

@addMethod(AnimatedComponent)
public func AddAdditiveTranslation(name: CName, translation: script_ref<Vector4>) {
    let entry = new AdditiveTransformEntry();
    entry.name = name;
    entry.transform = new QsTransform();
    entry.transform.Translation = Deref(translation);
    ArrayPush(this.additiveTransforms, entry);
}

@addMethod(AnimatedComponent)
public func AddAdditiveRotation(name: CName, rotation: script_ref<Quaternion>) {
    let entry = new AdditiveTransformEntry();
    entry.name = name;
    entry.transform = new QsTransform();
    entry.transform.Rotation = Deref(rotation);
    ArrayPush(this.additiveTransforms, entry);
}

@addMethod(AnimatedComponent)
public func RemoveAdditiveTransform(name: CName) {
    let i = ArraySize(this.additiveTransforms) - 1;
    while i >= 0 {
        if Equals(this.additiveTransforms[i].name, name) {
            ArrayErase(this.additiveTransforms, i);
            return;
        }
        i -= 1;
    }
}

@addMethod(AnimatedComponent)
public func RemoveAdditiveTransforms(name: CName) {
    let i = ArraySize(this.additiveTransforms) - 1;
    while i >= 0 {
        if Equals(this.additiveTransforms[i].name, name) {
            ArrayErase(this.additiveTransforms, i);
        }
        i -= 1;
    }
}

@addMethod(AnimatedComponent)
public func ClearAdditiveTransforms() {
    ArrayClear(this.additiveTransforms);
}


@addField(entISkinTargetComponent)
public let visualScale: Vector3;

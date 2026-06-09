
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


@addField(Entity)
public let additiveTransforms: array<AdditiveTransformEntry>;

@addMethod(Entity)
public func AddAdditiveTransform(name: CName, transform: script_ref<QsTransform>) {
    let entry = new AdditiveTransformEntry();
    entry.name = name;
    entry.transform = Deref(transform);
    ArrayPush(this.additiveTransforms, entry);
}

@addMethod(Entity)
public func AddAdditiveTranslation(name: CName, translation: script_ref<Vector4>) {
    let entry = new AdditiveTransformEntry();
    entry.name = name;
    entry.transform = new QsTransform();
    entry.transform.Translation = Deref(translation);
    ArrayPush(this.additiveTransforms, entry);
}

@addMethod(Entity)
public func AddAdditiveRotation(name: CName, rotation: script_ref<Quaternion>) {
    let entry = new AdditiveTransformEntry();
    entry.name = name;
    entry.transform = new QsTransform();
    entry.transform.Rotation = Deref(rotation);
    ArrayPush(this.additiveTransforms, entry);
}

@addMethod(Entity)
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

@addMethod(Entity)
public func RemoveAdditiveTransforms(name: CName) {
    let i = ArraySize(this.additiveTransforms) - 1;
    while i >= 0 {
        if Equals(this.additiveTransforms[i].name, name) {
            ArrayErase(this.additiveTransforms, i);
        }
        i -= 1;
    }
}

@addMethod(Entity)
public func ClearAdditiveTransforms() {
    ArrayClear(this.additiveTransforms);
}


@addMethod(AnimatedComponent)
public native func GetRig() -> ref<animRig>;

@addMethod(AnimatedComponent)
public native func ForceReferencePose(force: Bool);


@if(ModuleExists("Codeware"))

@addField(entISkinTargetComponent)
public let visualScale: Vector3;

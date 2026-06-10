@addField(Entity)
public let metaRigRef: MetaRigRef;

@addField(Entity)
public let metaPoseRef: MetaPoseRef;

@addField(Entity)
public let additiveTransforms: array<AdditiveTransformEntry>;

@addMethod(Entity)
public func GetMetaRig() -> MetaRigRef {
    return this.metaRigRef;
}

@addMethod(Entity)
public func GetMetaPose() -> MetaPoseRef {
    return this.metaPoseRef;
}

@addMethod(Entity)
public func AddBoneAdditiveTransform(name: CName, transform: script_ref<QsTransform>) {
    let entry = new AdditiveTransformEntry();
    entry.name = name;
    entry.transform = Deref(transform);
    ArrayPush(this.additiveTransforms, entry);
}

@addMethod(Entity)
public func AddBoneAdditiveTranslation(name: CName, translation: script_ref<Vector4>) {
    let entry = new AdditiveTransformEntry();
    entry.name = name;
    entry.transform = new QsTransform();
    entry.transform.Translation = Deref(translation);
    ArrayPush(this.additiveTransforms, entry);
}

@addMethod(Entity)
public func AddBoneAdditiveRotation(name: CName, rotation: script_ref<Quaternion>) {
    let entry = new AdditiveTransformEntry();
    entry.name = name;
    entry.transform = new QsTransform();
    entry.transform.Rotation = Deref(rotation);
    ArrayPush(this.additiveTransforms, entry);
}

@addMethod(Entity)
public func AddBoneAdditiveScale(name: CName, scale: Vector3) {
    let entry = new AdditiveTransformEntry();
    entry.name = name;
    entry.transform = new QsTransform();
    entry.transform.Scale = Vector4.Vector3To4(scale);
    ArrayPush(this.additiveTransforms, entry);
}

@addMethod(Entity)
public func RemoveBoneAdditiveTransform(name: CName) {
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
public func RemoveBoneAdditiveTransforms(name: CName) {
    let i = ArraySize(this.additiveTransforms) - 1;
    while i >= 0 {
        if Equals(this.additiveTransforms[i].name, name) {
            ArrayErase(this.additiveTransforms, i);
        }
        i -= 1;
    }
}

@addMethod(Entity)
public func ClearBoneAdditiveTransforms() {
    ArrayClear(this.additiveTransforms);
}

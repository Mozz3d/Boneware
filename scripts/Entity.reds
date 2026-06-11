@addField(Entity)
public let shouldAnimUpdate: Bool = true;

@addField(Entity)
public let metaRigRef: MetaRigRef;

@addField(Entity)
public let metaPoseRef: MetaPoseRef;

@addField(Entity)
public let poseAdditiveTransforms: array<BoneTransformEntry>;

@addField(Entity)
public let poseOverrideTransforms: array<BoneTransformEntry>;

@addField(Entity)
public let poseTrackOverrides: array<TrackValueEntry>;

@addMethod(Entity)
public func SetShouldAnimUpdate(shouldUpdate: Bool) {
    this.shouldAnimUpdate = shouldUpdate;
}

@addMethod(Entity)
public func ToggleShouldAnimUpdate() {
    this.shouldAnimUpdate = !this.shouldAnimUpdate;
}

@addMethod(Entity)
public func GetMetaRig() -> MetaRigRef {
    return this.metaRigRef;
}

@addMethod(Entity)
public func GetMetaPose() -> MetaPoseRef {
    return this.metaPoseRef;
}

@addMethod(Entity)
public func GetBoneNames() -> array<CName> {
    return MetaRigRef.GetBoneNames(this.metaRigRef);
}

@addMethod(Entity)
public func GetTrackNames() -> array<CName> {
    return MetaRigRef.GetTrackNames(this.metaRigRef);
}

@addMethod(Entity)
public func GetPoseTransforms() -> array<QsTransform> {
    return MetaPoseRef.GetTransforms(this.metaPoseRef);
}

@addMethod(Entity)
public func GetPoseTracks() -> array<Float> {
    return MetaPoseRef.GetTracks(this.metaPoseRef);
}

@addMethod(Entity)
public func SetPoseOverrideTransform(name: CName, transform: QsTransform) {
    let i = 0;
    while i < ArraySize(this.poseOverrideTransforms) {
        if Equals(this.poseOverrideTransforms[i].name, name) {
            this.poseOverrideTransforms[i].transform = transform;
            return;
        }
        i += 1;
    }
    let entry = new BoneTransformEntry();
    entry.name = name;
    entry.transform = transform;
    ArrayPush(this.poseOverrideTransforms, entry);
}

@addMethod(Entity)
public func RemovePoseOverrideTransform(name: CName) {
    let i = 0;
    while i < ArraySize(this.poseOverrideTransforms) {
        if Equals(this.poseOverrideTransforms[i].name, name) {
            ArrayErase(this.poseOverrideTransforms, i);
            return;
        }
        i += 1;
    }
}

@addMethod(Entity)
public func ClearPoseOverrideTransforms() {
    ArrayClear(this.poseOverrideTransforms);
}

@addMethod(Entity)
public func AddPoseAdditiveTransform(name: CName, transform: QsTransform) {
    let entry = new BoneTransformEntry();
    entry.name = name;
    entry.transform = transform;
    ArrayPush(this.poseAdditiveTransforms, entry);
}

@addMethod(Entity)
public func AddPoseAdditiveTranslation(name: CName, translation: Vector4) {
    let entry = new BoneTransformEntry();
    entry.name = name;
    entry.transform = new QsTransform();
    entry.transform.Translation = translation;
    ArrayPush(this.poseAdditiveTransforms, entry);
}

@addMethod(Entity)
public func AddPoseAdditiveRotation(name: CName, rotation: Quaternion) {
    let entry = new BoneTransformEntry();
    entry.name = name;
    entry.transform = new QsTransform();
    entry.transform.Rotation = rotation;
    ArrayPush(this.poseAdditiveTransforms, entry);
}

@addMethod(Entity)
public func AddPoseAdditiveScale(name: CName, scale: Vector3) {
    let entry = new BoneTransformEntry();
    entry.name = name;
    entry.transform = new QsTransform();
    entry.transform.Scale = Vector4.Vector3To4(scale);
    ArrayPush(this.poseAdditiveTransforms, entry);
}

@addMethod(Entity)
public func RemovePoseAdditiveTransform(name: CName) {
    let i = ArraySize(this.poseAdditiveTransforms) - 1;
    while i >= 0 {
        if Equals(this.poseAdditiveTransforms[i].name, name) {
            ArrayErase(this.poseAdditiveTransforms, i);
            return;
        }
        i -= 1;
    }
}

@addMethod(Entity)
public func RemovePoseAdditiveTransforms(name: CName) {
    let i = ArraySize(this.poseAdditiveTransforms) - 1;
    while i >= 0 {
        if Equals(this.poseAdditiveTransforms[i].name, name) {
            ArrayErase(this.poseAdditiveTransforms, i);
        }
        i -= 1;
    }
}

@addMethod(Entity)
public func ClearPoseAdditiveTransforms() {
    ArrayClear(this.poseAdditiveTransforms);
}

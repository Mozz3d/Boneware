@addField(Entity)
public let shouldAnimUpdate: Bool = true;

@addField(Entity)
public let metaRig: MetaRig;

@addField(Entity)
public let metaPose: MetaPose;


@addMethod(Entity)
public func SetShouldAnimUpdate(shouldUpdate: Bool) {
    this.shouldAnimUpdate = shouldUpdate;
}

@addMethod(Entity)
public func ToggleShouldAnimUpdate() {
    this.shouldAnimUpdate = !this.shouldAnimUpdate;
}

@addMethod(Entity)
public func GetMetaRig() -> MetaRig {
    return this.metaRig;
}

@addMethod(Entity)
public func GetMetaPose() -> MetaPose {
    return this.metaPose;
}

@addMethod(Entity)
public func GetBoneNames() -> array<CName> {
    return this.metaRig.GetBoneNames();
}

@addMethod(Entity)
public func GetBoneParentIndices() -> array<Int16> {
    return this.metaRig.GetBoneParentIndices();
}

@addMethod(Entity)
public func GetTrackNames() -> array<CName> {
    return this.metaRig.GetTrackNames();
}

@addMethod(Entity)
public func GetPoseTransforms() -> array<QsTransform> {
    return this.metaPose.GetTransforms();
}

@addMethod(Entity)
public func GetPoseTracks() -> array<Float> {
    return this.metaPose.GetTracks();
}

@addMethod(Entity)
public func SetPoseOverrideTransform(name: CName, transform: QsTransform) {
    this.metaPose.SetOverrideTransformLS(name, transform);
}

@addMethod(Entity)
public func RemovePoseOverrideTransform(name: CName) {
    this.metaPose.RemoveOverrideTransformLS(name);
}

@addMethod(Entity)
public func ClearPoseOverrideTransforms() {
    this.metaPose.ClearOverrideTransformsLS();
}

@addMethod(Entity)
public func AddPoseAdditiveTransform(name: CName, transform: QsTransform) {
    this.metaPose.AddAdditiveTransformLS(name, transform);
}

@addMethod(Entity)
public func RemovePoseAdditiveTransform(name: CName) {
    this.metaPose.RemoveAdditiveTransformLS(name);
}

@addMethod(Entity)
public func RemovePoseAdditiveTransforms(name: CName) {
    this.metaPose.RemovePoseAdditiveTransforms(name);
}

@addMethod(Entity)
public func ClearPoseAdditiveTransforms() {
    this.metaPose.ClearAdditiveTransformsLS();
}

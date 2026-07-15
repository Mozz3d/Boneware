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
    return MetaRig.GetBoneNames(this.metaRig);
}

@addMethod(Entity)
public func GetBoneParentIndices() -> array<Int16> {
    return MetaRig.GetParentIndices(this.metaRig);
}

@addMethod(Entity)
public func GetTrackNames() -> array<CName> {
    return MetaRig.GetTrackNames(this.metaRig);
}

@addMethod(Entity)
public func GetPoseTransformsLS() -> array<QsTransform> {
    return MetaPose.GetTransformsLS(this.metaPose);
}

@addMethod(Entity)
public func GetPoseTracks() -> array<Float> {
    return MetaPose.GetTracks(this.metaPose);
}

@addMethod(Entity)
public func SetPoseOverrideTransformLS(name: CName, transform: QsTransform) {
    MetaPose.SetOverrideTransformLS(this.metaPose, name, transform);
}

@addMethod(Entity)
public func RemovePoseOverrideTransformLS(name: CName) {
    MetaPose.RemoveOverrideTransformLS(this.metaPose, name);
}

@addMethod(Entity)
public func ClearPoseOverrideTransformsLS() {
    MetaPose.ClearOverrideTransformsLS(this.metaPose);
}

@addMethod(Entity)
public func AddPoseAdditiveTransformLS(name: CName, transform: QsTransform) {
    MetaPose.AddAdditiveTransformLS(this.metaPose, name, transform);
}

@addMethod(Entity)
public func RemovePoseAdditiveTransformLS(name: CName) {
    MetaPose.RemoveAdditiveTransformLS(this.metaPose, name);
}

@addMethod(Entity)
public func RemovePoseAdditiveTransformsLS(name: CName) {
    MetaPose.RemoveAdditiveTransformsLS(this.metaPose, name);
}

@addMethod(Entity)
public func ClearPoseAdditiveTransformsLS() {
    MetaPose.ClearAdditiveTransformsLS(this.metaPose);
}

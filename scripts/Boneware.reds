
public native struct BoneTransformEntry {
    public native let name: CName;
    public native let transform: QsTransform;
}

public native struct TrackValueEntry {
    public native let name: CName;
    public native let value: Float;
}

public native struct MetaPose {
    public native let overrideTransformsLS: array<BoneTransformEntry>;
    public native let additiveTransformsLS: array<BoneTransformEntry>;
    public native let overrideTracks: array<TrackValueEntry>;

    public func SetOverrideTransformLS(name: CName, transform: QsTransform) {
        let i = 0;
        while i < ArraySize(this.overrideTransformsLS) {
            if Equals(this.overrideTransformsLS[i].name, name) {
                this.overrideTransformsLS[i].transform = transform;
                return;
            }
            i += 1;
        }
        let entry = new BoneTransformEntry();
        entry.name = name;
        entry.transform = transform;
        ArrayPush(this.overrideTransformsLS, entry);
    }

    public func RemoveOverrideTransformLS(name: CName) {
        let i = 0;
        while i < ArraySize(this.overrideTransformsLS) {
            if Equals(this.overrideTransformsLS[i].name, name) {
                ArrayErase(this.overrideTransformsLS, i);
                return;
            }
            i += 1;
        }
    }

    public func ClearOverrideTransformsLS() {
        ArrayClear(this.overrideTransformsLS);
    }

    public func AddAdditiveTransformLS(name: CName, transform: QsTransform) {
        let entry = new BoneTransformEntry();
        entry.name = name;
        entry.transform = transform;
        ArrayPush(this.additiveTransformsLS, entry);
    }

    public func RemoveAdditiveTransformLS(name: CName) {
        let i = ArraySize(this.additiveTransformsLS) - 1;
        while i >= 0 {
            if Equals(this.additiveTransformsLS[i].name, name) {
                ArrayErase(this.additiveTransformsLS, i);
                return;
            }
            i -= 1;
        }
    }

    public func RemoveAdditiveTransformsLS(name: CName) {
        let i = ArraySize(this.additiveTransformsLS) - 1;
        while i >= 0 {
            if Equals(this.additiveTransformsLS[i].name, name) {
                ArrayErase(this.additiveTransformsLS, i);
            }
            i -= 1;
        }
    }

    public func ClearAdditiveTransformsLS() {
        ArrayClear(this.additiveTransformsLS);
    }

    private native let numBones: Uint32;
    private native let transformsLS: array<QsTransform>;
    private native let transformsMS: array<QsTransform>;
    private native let tracks: array<Float>;

    public func GetNumBones() -> Uint32 {
        return numBones;
    }

    public func GetTransformsLS() -> array<QsTransform> {
        return transformsLS;
    }

    public func GetTransformsMS() -> array<QsTransform> {
        return transformsMS;
    }
    
    public func GetTracks() -> array<Float> {
        return tracks;
    }
}

public native struct MetaRig {
    private native let transforms: array<QsTransform>;
    private native let parentIndices: array<Int16>;
    private native let boneNames: array<CName>;
    private native let tracks: array<Float>;
    private native let trackNames: array<CName>;

    public func GetTransforms() -> array<QsTransform> {
        return transforms;
    }
    
    public func GetParentIndices() -> array<Int16> {
        return parentIndices;
    }

    public func GetBoneNames() -> array<CName> {
        return boneNames;
    }
    
    public func GetTracks() -> array<Float> {
        return tracks;
    }
    
    public func GetTrackNames() -> array<CName> {
        return trackNames;
    }
}

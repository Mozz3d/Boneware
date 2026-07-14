
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

    public static func SetOverrideTransformLS(self: script_ref<MetaPose>, name: CName, transform: QsTransform) {
        let i = 0;
        while i < ArraySize(self.overrideTransformsLS) {
            if Equals(self.overrideTransformsLS[i].name, name) {
                self.overrideTransformsLS[i].transform = transform;
                return;
            }
            i += 1;
        }
        let entry = new BoneTransformEntry();
        entry.name = name;
        entry.transform = transform;
        ArrayPush(self.overrideTransformsLS, entry);
    }

    public static func RemoveOverrideTransformLS(self: script_ref<MetaPose>, name: CName) {
        let i = 0;
        while i < ArraySize(self.overrideTransformsLS) {
            if Equals(self.overrideTransformsLS[i].name, name) {
                ArrayErase(self.overrideTransformsLS, i);
                return;
            }
            i += 1;
        }
    }

    public static func ClearOverrideTransformsLS(self: script_ref<MetaPose>) {
        ArrayClear(self.overrideTransformsLS);
    }

    public static func AddAdditiveTransformLS(self: script_ref<MetaPose>, name: CName, transform: QsTransform) {
        let entry = new BoneTransformEntry();
        entry.name = name;
        entry.transform = transform;
        ArrayPush(self.additiveTransformsLS, entry);
    }

    public static func RemoveAdditiveTransformLS(self: script_ref<MetaPose>, name: CName) {
        let i = ArraySize(self.additiveTransformsLS) - 1;
        while i >= 0 {
            if Equals(self.additiveTransformsLS[i].name, name) {
                ArrayErase(self.additiveTransformsLS, i);
                return;
            }
            i -= 1;
        }
    }

    public static func RemoveAdditiveTransformsLS(self: script_ref<MetaPose>, name: CName) {
        let i = ArraySize(self.additiveTransformsLS) - 1;
        while i >= 0 {
            if Equals(self.additiveTransformsLS[i].name, name) {
                ArrayErase(self.additiveTransformsLS, i);
            }
            i -= 1;
        }
    }

    public static func ClearAdditiveTransformsLS(self: script_ref<MetaPose>) {
        ArrayClear(self.additiveTransformsLS);
    }

    private native let numBones: Uint32;
    private native let transformsLS: array<QsTransform>;
    private native let transformsMS: array<QsTransform>;
    private native let tracks: array<Float>;

    public static func GetNumBones(self: script_ref<MetaPose>) -> Uint32 {
        return self.numBones;
    }

    public static func GetTransformsLS(self: script_ref<MetaPose>) -> array<QsTransform> {
        return self.transformsLS;
    }

    public static func GetTransformsMS(self: script_ref<MetaPose>) -> array<QsTransform> {
        return self.transformsMS;
    }
    
    public static func GetTracks(self: script_ref<MetaPose>) -> array<Float> {
        return self.tracks;
    }
}

public native struct MetaRig {
    private native let transforms: array<QsTransform>;
    private native let parentIndices: array<Int16>;
    private native let boneNames: array<CName>;
    private native let tracks: array<Float>;
    private native let trackNames: array<CName>;

    public static func GetTransforms(self: script_ref<MetaRig>) -> array<QsTransform> {
        return self.transforms;
    }
    
    public static func GetParentIndices(self: script_ref<MetaRig>) -> array<Int16> {
        return self.parentIndices;
    }

    public static func GetBoneNames(self: script_ref<MetaRig>) -> array<CName> {
        return self.boneNames;
    }
    
    public static func GetTracks(self: script_ref<MetaRig>) -> array<Float> {
        return self.tracks;
    }
    
    public static func GetTrackNames(self: script_ref<MetaRig>) -> array<CName> {
        return self.trackNames;
    }
}

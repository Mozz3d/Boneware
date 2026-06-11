```lua
if ImGui.Button("Log Current Pose Transforms") then
    player = Game.GetPlayer()
    for i, transform in ipairs(player:GetPoseTransforms()) do 
        print(player:GetBoneNames()[i], GameDump(transform))
    end
end

if ImGui.Button("Log Current Pose Tracks") then
    player = Game.GetPlayer()
    for i, track in ipairs(player:GetPoseTracks()) do 
        print(player:GetBoneNames()[i], track)
    end
end

if ImGui.Button("Toggle Animation Updating") then
    player = Game.GetPlayer()
    player:ToggleShouldAnimUpdate()
end

if ImGui.Button("Set Pose Override Transform") then
    player = Game.GetPlayer()
    local transform = QsTrasnform.new()
    transform.Translation = ToVector4{x=1.5, y=1.5, z=1.5, w=1}
    player:SetPoseOverrideTransform("l_thigh_0_JNT", transform)
end

if ImGui.Button("Add Pose Additive Transform") then
    player = Game.GetPlayer()
    local transform = QsTrasnform.new()
    transform.Scale = ToVector4{x=1.1, y=1.1, z=1.1, w=1}
    player:AddPoseAdditiveTransform("l_thigh_0_JNT", transform)
end

if ImGui.Button("Sample Animation") then
    player = Game.GetPlayer()
    rootComponent = player:FindComponentByName('root')
    animSetup = rootComponent.animations.gameplay[2]
    animSet = animSetup:GetAnimSet() -- base\animations\player\female\body\player_locomotion.anims
    animation = animSet.animations[10].animation -- fpp_idle_to_jog_0
    sampledTransforms = animation:SampleTransforms(0.5) -- sample at 0.5s
    for i, transform in ipairs(sampledTransforms) do
        print(i, GameDump(transform))
    end
    sampledTracks = animation:SampleTracks(0.5) -- sample at 0.5s
    for i, track in ipairs(sampledTracks) do
        print(i, track)
    end
end

if ImGui.Button("Scale FPP Torso") then
    player = Game.GetPlayer()
    torso = player:FindComponentByName('t0_000_pwa_fpp__torso')
    torso.visualScale = ToVector3{x=2.0, y=2.0, z=2.0}
end
```

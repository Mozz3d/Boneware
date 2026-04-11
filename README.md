```lua
if ImGui.Button("Log Current Pose") then
    player = Game.GetPlayer()
    rootComponent = player:FindComponentByName('root')
    poseTransforms = rootComponent:GetCurrentPoseTransforms()
    for i, transform in ipairs(poseTransforms) do 
        print(i, GameDump(transform))
    end
end

if ImGui.Button("Sample Animation") then
    player = Game.GetPlayer()
    rootComponent = player:FindComponentByName('root')
    animSetup = rootComponent.animations.gameplay[2]
    animSet = animSetup:GetAnimSet() -- base\animations\player\female\body\player_locomotion.anims
    animation = animSet.animations[10].animation -- fpp_idle_to_jog_0
    sampled = animation:SampleTransforms(0.5) -- sample at 0.5s
    for i, transform in ipairs(sampled) do
        print(i, GameDump(transform))
    end
end
```

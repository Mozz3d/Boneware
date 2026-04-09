```lua
if ImGui.Button("Log Current Pose") then
    player = Game.GetPlayer()
    rootComponent = player:FindComponentByName('root')
    poseTransforms = rootComponent:GetCurrentPoseTransforms()
    for i, transform in ipairs(poseTransforms) do 
        print(i, GameDump(transform))
    end
end
```
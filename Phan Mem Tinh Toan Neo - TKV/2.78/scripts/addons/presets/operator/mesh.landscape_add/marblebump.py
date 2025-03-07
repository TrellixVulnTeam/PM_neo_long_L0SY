import bpy
op = bpy.context.active_operator

op.AutoUpdate = True
op.SphereMesh = False
op.SmoothMesh = True
op.Subdivision = 128
op.MeshSize = 2.0
op.XOffset = 0.0
op.YOffset = 0.0
op.RandomSeed = 3
op.NoiseSize = 0.5
op.NoiseType = 'marble_noise'
op.BasisType = '3'
op.VLBasisType = '0'
op.Distortion = 0.25
op.HardNoise = False
op.NoiseDepth = 2
op.mDimension = 1.0
op.mLacunarity = 2.0
op.mOffset = 1.0
op.mGain = 1.0
op.MarbleBias = '0'
op.MarbleSharp = '2'
op.MarbleShape = '3'
op.Invert = False
op.Height = 0.25
op.Offset = 0.0
op.Falloff = '0'
op.Sealevel = 0.0
op.Plateaulevel = 1.0
op.Strata = 3.0
op.StrataType = '0'

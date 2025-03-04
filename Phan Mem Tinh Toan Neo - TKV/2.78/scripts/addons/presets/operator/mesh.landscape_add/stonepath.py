import bpy
op = bpy.context.active_operator

op.AutoUpdate = True
op.SphereMesh = False
op.SmoothMesh = True
op.Subdivision = 128
op.MeshSize = 2.0
op.XOffset = 0.0
op.YOffset = 0.0
op.RandomSeed = 21
op.NoiseSize = 0.25
op.NoiseType = 'ridged_multi_fractal'
op.BasisType = '7'
op.VLBasisType = '3'
op.Distortion = 1.5
op.HardNoise = False
op.NoiseDepth = 4
op.mDimension = 1.0
op.mLacunarity = 2.880000114440918
op.mOffset = 1.2000000476837158
op.mGain = 3.0
op.MarbleBias = '0'
op.MarbleSharp = '0'
op.MarbleShape = '0'
op.Invert = False
op.Height = 0.30000001192092896
op.Offset = 0.10000000149011612
op.Falloff = '3'
op.Sealevel = 0.0
op.Plateaulevel = 0.11999999731779099
op.Strata = 5.0
op.StrataType = '0'

xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 23;
 -0.61803;0.00000;1.90211;,
 -1.61803;0.00000;1.17557;,
 0.00000;0.00000;0.00000;,
 0.61803;0.00000;1.90211;,
 1.61803;0.00000;1.17557;,
 2.00000;0.00000;-0.00000;,
 1.61803;0.00000;-1.17557;,
 0.61803;0.00000;-1.90211;,
 -0.61803;0.00000;-1.90211;,
 -1.61803;0.00000;-1.17557;,
 -2.00000;0.00000;0.00000;,
 -1.61803;0.00000;1.17557;,
 -0.61803;0.00000;1.90211;,
 0.00000;7.00000;0.00000;,
 0.61803;0.00000;1.90211;,
 1.61803;0.00000;1.17557;,
 2.00000;0.00000;-0.00000;,
 1.61803;0.00000;-1.17557;,
 0.61803;0.00000;-1.90211;,
 -0.61803;0.00000;-1.90211;,
 -1.61803;0.00000;-1.17557;,
 -2.00000;0.00000;0.00000;,
 -1.61803;0.00000;1.17557;;
 
 20;
 3;0,1,2;,
 3;3,0,2;,
 3;4,3,2;,
 3;5,4,2;,
 3;6,5,2;,
 3;7,6,2;,
 3;8,7,2;,
 3;9,8,2;,
 3;10,9,2;,
 3;1,10,2;,
 3;11,12,13;,
 3;12,14,13;,
 3;14,15,13;,
 3;15,16,13;,
 3;16,17,13;,
 3;17,18,13;,
 3;18,19,13;,
 3;19,20,13;,
 3;20,21,13;,
 3;21,22,13;;
 
 MeshMaterialList {
  1;
  20;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  15;
  0.000000;-1.000000;0.000000;,
  0.000000;0.297297;0.954785;,
  -0.777889;0.274721;0.565170;,
  -0.297127;0.274721;0.914464;,
  0.297127;0.274721;0.914464;,
  0.777889;0.274721;0.565169;,
  0.961524;0.274721;-0.000000;,
  0.908055;0.297297;-0.295045;,
  0.777889;0.274721;-0.565170;,
  0.297127;0.274721;-0.914464;,
  -0.297127;0.274721;-0.914464;,
  -0.561209;0.297297;-0.772437;,
  -0.777889;0.274721;-0.565170;,
  -0.961524;0.274721;-0.000000;,
  -0.917777;0.262222;0.298204;;
  20;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;2,3,1;,
  3;3,4,1;,
  3;4,5,1;,
  3;5,6,7;,
  3;6,8,7;,
  3;8,9,7;,
  3;9,10,11;,
  3;10,12,11;,
  3;12,13,11;,
  3;13,2,14;;
 }
 MeshTextureCoords {
  23;
  0.577254;0.012236;,
  0.702254;0.103054;,
  0.500000;0.250000;,
  0.422746;0.012236;,
  0.297746;0.103054;,
  0.250000;0.250000;,
  0.297746;0.396946;,
  0.422746;0.487764;,
  0.577254;0.487764;,
  0.702254;0.396946;,
  0.750000;0.250000;,
  0.250000;0.500000;,
  0.300000;0.500000;,
  0.500000;1.000000;,
  0.350000;0.500000;,
  0.400000;0.500000;,
  0.450000;0.500000;,
  0.500000;0.500000;,
  0.550000;0.500000;,
  0.600000;0.500000;,
  0.650000;0.500000;,
  0.700000;0.500000;,
  0.750000;0.500000;;
 }
}

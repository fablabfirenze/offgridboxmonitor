float quantizedHeightToLiters(float height){
  int wlaSize = 115;
  // int inx = map(height, 0, 115,0,wlaSize);
  int inx = (int)height;
  inx = min(inx,wlaSize);
  inx = max(inx,0);

  int val = waterLevels[inx];
  return (float)val/1000.0;
}

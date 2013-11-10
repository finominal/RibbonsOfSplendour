void InitializeRibbons()
{
  //Zero indexed, includes space character 
  RIBBONS[0].length = 11; //seconds one  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ' '  
  RIBBONS[1].length = 6;  //seconds tens 0, 1, 2, 3, 4, 5, ' '
  
  RIBBONS[2].length = 11; //minutes one  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ' ' 
  RIBBONS[3].length = 6; 
  
  RIBBONS[4].length = 11; //hours one    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ' ' 
  RIBBONS[5].length = 5;  //hours tens   0, 1, 2, ' ' 
  
  RIBBONS[6].length = 11; //years ones   0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ' ' 
  RIBBONS[7].length = 11; //years tens   0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ' '
  RIBBONS[8].length = 5; //years hund   0, 1, 2, 3, ' '
}

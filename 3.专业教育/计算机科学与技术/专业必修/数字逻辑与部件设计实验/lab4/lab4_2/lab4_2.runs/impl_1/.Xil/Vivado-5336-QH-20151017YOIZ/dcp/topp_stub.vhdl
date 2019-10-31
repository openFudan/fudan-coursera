-- Copyright 1986-2015 Xilinx, Inc. All Rights Reserved.
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity topp is
  Port ( 
    clk : in STD_LOGIC;
    s : in STD_LOGIC_VECTOR ( 14 downto 0 );
    q : out STD_LOGIC_VECTOR ( 15 downto 0 )
  );

end topp;

architecture stub of topp is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
begin
end;

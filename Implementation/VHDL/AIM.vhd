library ieee ;
use ieee.std_logic_1164.all ;

entity myServer is 
		port(rst,clk : in bit;
                car:in std_logic_vector(7 downto 0 );
		signal_car:out std_logic_vector(7 downto 0));
end entity myServer;

architecture behavioral of myServer is 

type state is (idle,make_queue,get_signal);

signal current_state,next_state:state;

begin

state_memory:process(clk,rst)
	begin
	if rst='1'then 
	current_state <= idle;
	elsif(clk='1' and clk' event) then
		current_state<=next_state;
		end if;
		end process;



input_comb:process(current_state,car)

begin 
	case current_state is 
		when idle => if car="00000001" then	
				next_state<= idle;
				elsif(car="00000010") then
				next_state<=make_queue;
				end if;

		when make_queue=> if car="00000011" then
				next_state<=get_signal;
				--else next_state <= make_queue;
				end if;

		when get_signal=> if car="00000100" then
					next_state <= idle;
					elsif(car="00000011") then
					next_state <= get_signal;
					end if;
		end case;
		end process;


output_comb:process(current_state, car)

begin
    case current_state is 

             when idle => if car = "00000001" then
                          signal_car <= "00000001";
                          elsif (car = "00000010")  then signal_car <= "00000010";
                          end if;

             when make_queue => if car= "00000011" then
                                signal_car <= "00000011";
                                else signal_car <= "00000100";
                                end if;

             when get_signal => if car= "00000100" then
                                signal_car <= "00000100";
                                elsif(car= "00000011") then signal_car <= "00000100";
                                end if;
end case;
end process;
end architecture;

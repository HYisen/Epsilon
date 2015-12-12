Available Instructions

(args) means optional args
[args] means necessary args
<info> is just extra information to explain
... means more of the preview args is allowed

quit

save (filename<string>)
load (filename<string>)

print (limit<addr or type>)

add [id<int>],[type<int>],[status<int>],[location<int>],[info<string>]
del [id<int>]

slip [aimed_status<int>] [id1<int>],[id2<int>],...
move [aimed_location<int>] [id1<int>],[id2<int>],...
edit [aimed_info<string>] [id1<int>],[id2<int>],...

show <to show the history>
undo (target) <to undo until the target record>
TODO : mettre à jour ce README pour catkin

Pour générer un service et un message:

dans CMakeLists.txt, décommenter 	# rosbuild_gensrv()
et									# rosbuild_genmsg()

Liste du service disponible via le noeud ExecuteurDeChemin 

- Service :

	Request :

		/Command
		
			uint8	EXECUTE_PATH	= 0
			uint8	PAUSE			= 1
			uint8	RESUME			= 2
			uint8	CANCEL			= 3

			uint8 	type

			uint8	ID
			
	---		
	
	Response :
	
		/Command
		
			bool	accepted
			
Topic :

	/EdCState
			
		uint8	FREE			= 0
		uint8	IN_PROGRESS		= 1
		uint8	FINISHED		= 2
		uint8	BAD_ID			= 3
		uint8	OBSTACLE		= 4
		uint8	PROBLEM			= 5

		uint8	state
